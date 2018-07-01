let component = ReasonReact.statelessComponent("SF_TextInput");

let make = _children => {
  ...component,
  render: _self =>
    <div className="sf-input-container"> <input _type="text" /> </div>,
};