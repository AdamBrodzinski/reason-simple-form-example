open SF_Types;
let component = ReasonReact.statelessComponent("SF_Form");

module Context =
  ReasonReactContext.CreateContext({
    type state = list(schemaItem);
    let name = "FormContext";
    let defaultValue: list(schemaItem) = [
      {name: "firstName", label: "First name"},
      {name: "lastName", label: "Last name"},
    ];
  });

let make = (~schema, children) => {
  ...component,
  render: _self =>
    <Context.Provider value=schema>
      <div className="sf-form-container">
        (
          ReasonReact.createDomElement(
            "form",
            ~props={"className": "sf-form"},
            children,
          )
        )
      </div>
    </Context.Provider>,
};