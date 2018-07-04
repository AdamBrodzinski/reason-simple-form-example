open SF_Types;

type action =
  | Submitted;

type state = formState;

module Context =
  ReasonReactContext.CreateContext({
    type state = context;
    let name = "FormContext";
    let defaultValue: context = {
      schemas: [
        {name: "firstName", label: "First name"},
        {name: "lastName", label: "Last name"},
      ],
    };
  });

let component = ReasonReact.reducerComponent("SF_Form");

let getInitialState = () : state => {submitted: false};

let make = (~schema, children) => {
  ...component,
  initialState: getInitialState,
  reducer: (action, _state) =>
    switch (action) {
    | Submitted => ReasonReact.Update({submitted: true})
    },
  render: self => {
    let contextValue: context = {schemas: schema};
    Js.log(self.state);
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