open SF_Types;
let component = ReasonReact.statelessComponent("SF_Form");

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

let make = (~schema, children) => {
  ...component,
  render: _self => {
    let contextValue: context = {schemas: schema};
    <Context.Provider value=contextValue>
      <div className="sf-form-container">
        (
          ReasonReact.createDomElement(
            "form",
            ~props={"className": "sf-form"},
            children,
          )
        )
      </div>
    </Context.Provider>;
  },
};