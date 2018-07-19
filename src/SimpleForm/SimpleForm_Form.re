[%%debugger.chrome];
open SimpleForm_Types;
module U = SimpleForm_Utils;

type action =
  | Initialized(formState)
  | Submitted
  | InputChanged(string, string)
  | InputBlurred(string);

type state = formState;

/* create default states for each input based on form schema */
let getInitialState = () : formState => {
  initialized: false,
  submitted: false,
  inputStates: [],
};

let createInputStatesFromSchema = schemas : list(inputState) =>
  schemas
  |> List.map((schema: schemaItem) =>
       {name: schema.name, valid: true, value: "", dirty: false}
     );

/* temp hack to simulate React context until v16 is released */
module Context =
  ReasonReactContext.CreateContext({
    type state = context;
    let name = "FormContext";
    let defaultValue: context = {
      formState: getInitialState(),
      schemas: [],
      updateInput: (_, _) => (),
      sendInputBlur: _ => (),
    };
  });

let component = ReasonReact.reducerComponent("SimpleForm_Form");

let make = (~schema: list(schemaItem), ~onSubmit, children) => {
  let handleInputChanged = (name, value, oldState) => {
    let newInputStates =
      oldState.inputStates
      |> List.map((x: inputState) => x.name == name ? {...x, value} : x);
    ReasonReact.Update({...oldState, inputStates: newInputStates});
  };

  let handleInputBlurred = (name, oldState) => {
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
        onSubmit(self.state);
        ();
      },
    );

  {
    ...component,
    didMount: self => {
      /* initialize state lazily for context library */
      let inputStates = createInputStatesFromSchema(schema);
      let newState = {...self.state, initialized: true, inputStates};
      self.send(Initialized(newState));
    },
    initialState: () => getInitialState(),
    reducer: (action, state) =>
      switch (action) {
      | Initialized(newState) => ReasonReact.Update(newState)
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
      List.length(self.state.inputStates) > 0 ?
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
        </Context.Provider> :
        ReasonReact.null;
    },
  };
};