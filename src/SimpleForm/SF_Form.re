let component = ReasonReact.statelessComponent("SF_Form");

type schemaItem = {
  name: string,
  label: string,
};
type schemaList = list(schemaItem);

module Context =
  ReasonReactContext.CreateContext({
    type state = schemaList;
    let name = "FormContext";
    let defaultValue = [
      {name: "firstName", label: "First name"},
      {name: "lastName", label: "Last name"},
    ];
  });

let make = (~schema: schemaList, children) => {
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