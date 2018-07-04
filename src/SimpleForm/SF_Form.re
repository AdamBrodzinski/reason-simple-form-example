open SF_Types;

type action =
  | Submitted
  | InputChanged(string, string);

type state = formState;

let hardcodedSchema: list(schemaItem) = [
  {name: "firstName", label: "First name"},
  {name: "lastName", label: "Last name"},
];

/* create default states for each input based on form schema */
let getInitialState = (schemas: list(schemaItem)) : state => {
  submitted: false,
  inputStates:
    List.map(
      (x: schemaItem) => {name: x.name, value: "", dirty: false},
      schemas,
    ),
};

let handleInputChanged = (name, newText, oldState) => {
  Js.log("input " ++ name ++ ": " ++ newText);
  ReasonReact.Update({...oldState, submitted: true});
};

/* let sendInputChanged = (name: string, value: string) => */

module Context =
  ReasonReactContext.CreateContext({
    type state = context;
    let name = "FormContext";
    let defaultValue: context = {
      formState: getInitialState(hardcodedSchema),
      schemas: hardcodedSchema,
      updateInput: (_, _) => (),
      /* handleInputChanged, */
    };
  });

let component = ReasonReact.reducerComponent("SF_Form");

let make = (~schema, children) => {
  ...component,
  initialState: () => getInitialState(schema),
  reducer: (action, state) =>
    switch (action) {
    | Submitted => ReasonReact.Update({...state, submitted: true})
    | InputChanged(name, newText) => handleInputChanged(name, newText, state)
    },
  render: self => {
    let updateInput = (name, text) => {
      self.send(InputChanged(name, text));
      ();
    };
    let contextValue: context = {
      schemas: schema,
      formState: self.state,
      updateInput,
    };
    Js.log(contextValue);
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
                Js.log("submit");
              },
            },
            children,
          )
        )
      </div>
    </Context.Provider>;
  },
};