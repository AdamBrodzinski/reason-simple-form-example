let component = ReasonReact.statelessComponent("SF_TextInput");
type formEv = ReactEventRe.Form.t;

let handleChange = (event: formEv) => {
  let foo = SF_Utils.getEventValue(event);
  Js.log(foo);
};

let make = (~name, ~_autoFocus=?, _children) => {
  ...component,
  render: _self =>
    <div className="sf-input-container">
      <input type_="text" name onChange=handleChange />
    </div>,
};