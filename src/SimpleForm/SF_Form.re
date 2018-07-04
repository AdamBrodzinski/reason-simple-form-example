open SF_Types;

type action =
  | Submitted;

type state = formState;

let getInitialState = () : state => {submitted: false};

module Context =
  ReasonReactContext.CreateContext({
    type state = context;
    let name = "FormContext";
    let defaultValue: context = {
      formState: getInitialState(),
      schemas: [
        {name: "firstName", label: "First name"},
        {name: "lastName", label: "Last name"},
      ],
    };
  });

let component = ReasonReact.reducerComponent("SF_Form");

let make = (~schema, children) => {
  ...component,
  initialState: getInitialState,
  reducer: (action, _state) =>
    switch (action) {
    | Submitted => ReasonReact.Update({submitted: true})
    },
  render: self => {
    let contextValue: context = {schemas: schema, formState: self.state};
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