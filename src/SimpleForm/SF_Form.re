[%%debugger.chrome];
open SF_Types;
module U = SimpleForm_Utils;

type action =
  | Initialized(formState)
  | Submitted
  | InputChanged(string, string);

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
    };
  });

let component = ReasonReact.reducerComponent("SF_Form");

let make = (~schema: list(schemaItem), ~onSubmit, children) => {
  let handleInputChanged = (name, value, oldState) => {
    let valid = false;
    let newInputStates =
      oldState.inputStates
      |> List.map(x => x.name == name ? {name, value, valid, dirty: true} : x);
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
      },
    render: self => {
      let contextValue: context = {
        schemas: schema,
        formState: self.state,
        updateInput: (name, text) => self.send(InputChanged(name, text)),
      };
      List.length(self.state.inputStates) > 0 ?
        <Context.Provider value=contextValue>
          <div className="sf-form-container">
            (
              ReasonReact.createDomElement(
                "form",
                ~props={
                  "className": "sf-form",
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