[%bs.raw {|require('./App.css')|}];
let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: _self =>
    <div className="App">
      <div className="App container"> <MyForm /> </div>
    </div>,
};