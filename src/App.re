[%bs.raw {|require('./App.css')|}];
let component = ReasonReact.statelessComponent("App");
let text = ReasonReact.string;

let make = _children => {
  ...component,
  render: _self =>
    <div className="App">
      <div className="container">
        <h2> (text("Login Form")) </h2>
        <MyForm />
      </div>
    </div>,
};