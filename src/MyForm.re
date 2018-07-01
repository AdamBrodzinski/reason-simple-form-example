[%bs.raw {|require('./App.css')|}];
let component = ReasonReact.statelessComponent("MyForm");

let make = _children => {
  ...component,
  render: _self =>
    <div className="MyForm"> (ReasonReact.string("Form")) </div>,
};