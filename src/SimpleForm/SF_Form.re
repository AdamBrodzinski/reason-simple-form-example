[%%debugger.chrome];
open SF_Types;

type action =
  | Initialized(formState)
  | Submitted
  | InputChanged(string, string);

type state = formState;

let hardcodedSchema: list(schemaItem) = [
  {name: "firstName", label: "First name"},
  {name: "lastName", label: "Last name"},
  {name: "age", label: "Age"},
];

/* create default states for each input based on form schema */
let getInitialState = (schemas: list(schemaItem)) : state => {
  initialized: false,
  submitted: false,
  inputStates:
    List.map(
      (x: schemaItem) => {name: x.name, value: "", dirty: false},
      schemas,
    ),
};

/* temp hack to simulate React context until v16 is released */
module Context =
  ReasonReactContext.CreateContext({
    type state = context;
    let name = "FormContext";
    let defaultValue: context = {
      formState: getInitialState(hardcodedSchema),
      schemas: hardcodedSchema,
      updateInput: (_, _) => (),
    };
  });

let component = ReasonReact.reducerComponent("SF_Form");

let make = (~schema, ~onSubmit, children) => {
  let handleInputChanged = (name, newText, oldState) => {
    let newInputState =
      List.map(
        x => x.name == name ? {name, value: newText, dirty: true} : x,
        oldState.inputStates,
      );
    ReasonReact.Update({...oldState, inputStates: newInputState});
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
      let newState = {...self.state, initialized: true};
      self.send(Initialized(newState));
    },
    initialState: () => getInitialState(schema),
    reducer: (action, state) =>
      switch (action) {
      | Initialized(newState) => ReasonReact.Update(newState)
      | Submitted => handleSubmitAction(onSubmit, state)
      | InputChanged(name, newTxt) => handleInputChanged(name, newTxt, state)
      },
    render: self => {
      let contextValue: context = {
        schemas: schema,
        formState: self.state,
        updateInput: (name, text) => self.send(InputChanged(name, text)),
      };
      self.state.initialized ?
        <Context.Provider value=contextValue>
          <div className="sf-form-container">
            (
              ReasonReact.createDomElement(
                "form",
                ~props={
                  "className": "sf-form",
                  "onSubmit": event => {
                    SF_Utils.preventDefault(event);
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