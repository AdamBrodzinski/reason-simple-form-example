[%%debugger.chrome];
open SimpleForm_Types;
module U = SimpleForm_Utils;
module V = SimpleForm_Validate;

type action =
  | Submitted
  | InputChanged(string, string)
  | InputBlurred(string);

type state = formState;

/** build out the states for each input in the schem and run an init validation */
let createInitalState = schema => {
  let inputStates =
    schema
    |> List.map((iSchema: schemaItem) =>
         {
           name: iSchema.name,
           valid: true,
           value: "",
           dirty: false,
           errors: [],
         }
       );

  let initialState = {submitted: false, inputStates};

  let newInputStates =
    initialState.inputStates
    |> List.map((x: inputState) => {
         let inputState = U.findStateByName(inputStates, x.name);
         let inputSchema = U.findSchemaByName(schema, x.name);

         let errors =
           V.validateInput(inputSchema, inputState, initialState)
           |> List.filter(x => x.isValid == false);

         {...x, valid: List.length(inputState.errors) == 0, errors};
       });

  {submitted: false, inputStates: newInputStates};
};

/*
  temp hack to simulate React context until v16 is released. NOTE we
  need to have things stubbed for the initial render of context, then
  on the 2nd render we get the values passed into the context `value`
 */
module Context =
  ReasonReactContext.CreateContext({
    type state = context;
    let name = "FormContext";
    let defaultValue: context = {
      formState: {
        submitted: false,
        inputStates: [],
      },
      schemas: [],
      updateInput: (_, _) => (),
      sendInputBlur: _ => (),
    };
  });

let component = ReasonReact.reducerComponent("SimpleForm_Form");

let make = (~schema: list(schemaItem), ~onSubmit, ~debug=false, children) => {
  let handleInputChanged = (name, value, oldState) => {
    if (debug) {
      Js.log("input changed: " ++ name ++ " - " ++ value);
    };
    let newInputStates =
      oldState.inputStates
      |> List.map((x: inputState) => x.name == name ? {...x, value} : x);

    let newState = {...oldState, inputStates: newInputStates};
    let inputState = U.findStateByName(newInputStates, name);
    let inputSchema = U.findSchemaByName(schema, name);

    let errors =
      V.validateInput(inputSchema, inputState, newState)
      |> List.filter(x => x.isValid == false);

    let newInputStates =
      newState.inputStates
      |> List.map((x: inputState) =>
           x.name == name ?
             {...x, valid: List.length(inputState.errors) == 0, errors} : x
         );

    ReasonReact.Update({...oldState, inputStates: newInputStates});
  };

  let handleInputBlurred = (name, oldState) => {
    if (debug) {
      Js.log("input blurred: " ++ name);
    };

    let newInputStates =
      oldState.inputStates
      |> List.map((x: inputState) =>
           x.name == name ? {...x, dirty: true} : x
         );
    ReasonReact.Update({...oldState, inputStates: newInputStates});
  };

  let handleSubmitAction = (onSubmit, state) =>
    ReasonReact.UpdateWithSideEffects(
      {...state, submitted: true},
      self => {
        if (debug) {
          Js.log("submitted: ");
          Js.log({
            "submitted": self.state.submitted,
            "inputStates": self.state.inputStates |> Array.of_list,
          });
        };
        onSubmit(self.state);
        ();
      },
    );

  {
    ...component,
    initialState: () => createInitalState(schema),
    reducer: (action, state) =>
      switch (action) {
      | Submitted => handleSubmitAction(onSubmit, state)
      | InputChanged(name, newTxt) => handleInputChanged(name, newTxt, state)
      | InputBlurred(name) => handleInputBlurred(name, state)
      },
    render: self => {
      let contextValue: context = {
        schemas: schema,
        formState: self.state,
        updateInput: (name, text) => self.send(InputChanged(name, text)),
        sendInputBlur: name => self.send(InputBlurred(name)),
      };
      <Context.Provider value=contextValue>
        <div className="SimpleForm_Form-container">
          (
            ReasonReact.createDomElement(
              "form",
              ~props={
                "className": "SimpleForm_Form",
                "onSubmit": event => {
                  U.preventDefault(event);
                  self.send(Submitted);
                },
              },
              children,
            )
          )
        </div>
      </Context.Provider>;
    },
  };
};