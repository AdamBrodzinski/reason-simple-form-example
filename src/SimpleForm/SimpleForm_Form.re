open SimpleForm_Types;
module U = SimpleForm_Utils;
module V = SimpleForm_Validate;

/** Throw if the user has declared an input in their schema but it's not
 *  present in the DOM. This is optional and can be turned off if you
 * know that it's not present at render but will be in the future.
 */
exception InputNotInForm(string);

type action =
  | Loading
  | Loaded
  | Submitted
  | InputChanged(string, string)
  | InputBlurred(string);

type state = formState;

/*
  temp hack to simulate React context until v16 is released. NOTE we
  need to have things stubbed for the initial render of context because
  passing in the real context before rendering doesn't work, it will always
  render the initial context once.
  https://github.com/Hehk/reason-react-context/issues/5
 */
module Context =
  ReasonReactContext.CreateContext({
    type state = context;
    let name = "FormContext";
    let defaultValue: context = {
      formState: {
        submitted: false,
        loading: false,
        isValid: false,
        inputStates: [],
      },
      schemas: [],
      updateInput: (_, _) => (),
      sendInputBlur: _ => (),
    };
  });

let component = ReasonReact.reducerComponent("SimpleForm_Form");

let createInitalState = schema => {
  /* TODO refactor this mess >.< */
  let inputStates =
    schema
    |> List.map((iSchema: schemaItem) =>
         {
           name: iSchema.name,
           valid: true,
           value: iSchema.initialValue,
           dirty: false,
           errors: [],
         }
       );

  let initialState = {
    submitted: false,
    loading: false,
    isValid: false,
    inputStates,
  };

  let newInputStates =
    initialState.inputStates
    |> List.map((x: inputState) => {
         let inputState = U.findStateByName(inputStates, x.name);
         let inputSchema = U.findSchemaByName(schema, x.name);

         let errors =
           V.validateInput(inputSchema, inputState, initialState)
           |> List.filter((x: validationResult) => x.isValid == false);

         {...x, valid: List.length(errors) == 0, errors};
       });

  {
    submitted: false,
    loading: false,
    isValid: false,
    inputStates: newInputStates,
  };
};

let inputIsPresent: string => bool = [%bs.raw
  {|
    function (name) {
      return !! document.getElementsByName(name).length;
    }
  |}
];

let make = (~schema: list(schemaItem), ~onSubmit, ~debug=false, ~presenceCheck=true, children) => {
  let handleInputChanged = (name, value, oldState) => {
    if (debug) {
      Js.log("Input Changed: " ++ name ++ " - " ++ value);
    };

    let updateValueIfMatchesName = (name, value, x: inputState) => 
      x.name == name ? {...x, value} : x;

    let newInputStates =
      oldState.inputStates
      |> List.map(updateValueIfMatchesName(name, value));

    let newState = {...oldState, inputStates: newInputStates};
    let inputState = U.findStateByName(newInputStates, name);
    let inputSchema = U.findSchemaByName(schema, name);

    let errors =
      V.validateInput(inputSchema, inputState, newState)
      |> List.filter((x: validationResult) => x.isValid == false);

    let newInputStates =
      newState.inputStates
      |> List.map((x: inputState) =>
           x.name == name ?
             {...x, valid: List.length(inputState.errors) == 0, errors} : x
         );

    let formIsValid =
      newInputStates
      |> List.map((x: inputState) => List.length(x.errors) > 0)
      |> List.filter(b => b == true)
      |> List.length == 0;

    ReasonReact.Update({
      ...oldState,
      isValid: formIsValid,
      inputStates: newInputStates,
    });
  };

  let handleInputBlurred = (name, oldState) => {
    if (debug) {
      Js.log("Input Blurred: " ++ name);
    };

    let newInputStates =
      oldState.inputStates
      |> List.map((x: inputState) =>
           x.name == name ? {...x, dirty: true} : x
         );
    ReasonReact.Update({...oldState, inputStates: newInputStates});
  };

  let handleSubmitAction = (onSubmit, state) => {
    let isValid = V.isFormValid(state, schema);
    let newState = {...state, isValid, submitted: true};
    ReasonReact.UpdateWithSideEffects(
      newState,
      self => {
        if (debug) {
          Js.log("submitted state: ");
          Js.log(SimpleForm_Debug.formatFormState(self.state));
        };
        if (isValid) {
          self.send(Loading);
        }
        onSubmit(~sendLoaded=(() => self.send(Loaded)), self.state);
        ();
      },
    );
  };

  {
    ...component,
    initialState: () => createInitalState(schema),
    didMount: self => {
      if (debug) {
        Js.log("Initial Form State:");
        Js.log(SimpleForm_Debug.formatFormState(self.state));
      };

      /* TODO use React 16 error boundry to display and error */
      if (presenceCheck) {
        let _ = Js.Global.setTimeout(() => { 
          List.map((item: schemaItem) => {
            if (inputIsPresent(item.name) == false) {
              let notFoundMsg = "You passed in a schema item for '" ++ item.name ++
                "' and we can not find it in the DOM. Please insert the input or remove the unused schema item.";
              raise(InputNotInForm(notFoundMsg));
            }
            item;
          }, schema) |> ignore;
        }, 1000);
      }
    },
    reducer: (action, state) =>
      switch (action) {
      | Submitted => handleSubmitAction(onSubmit, state)
      | InputChanged(name, newTxt) => handleInputChanged(name, newTxt, state)
      | InputBlurred(name) => handleInputBlurred(name, state)
      | Loading => ReasonReact.Update({...state, loading: true});
      | Loaded => ReasonReact.Update({...state, loading: false});
      },
    render: self => {
      <Context.Provider value={
        schemas: schema,
        formState: self.state,
        updateInput: (name, text) => self.send(InputChanged(name, text)),
        sendInputBlur: name => self.send(InputBlurred(name)),
      }>
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