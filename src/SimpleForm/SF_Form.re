let component = ReasonReact.statelessComponent("SF_Form");

type schemaItem = {
  name: string,
  label: string,
};

let make = children => {
  ...component,
  render: _self =>
    <div className="sf-form-container">
      (
        ReasonReact.createDomElement(
          "form",
          ~props={"className": "sf-form"},
          children,
        )
      )
    </div>,
};