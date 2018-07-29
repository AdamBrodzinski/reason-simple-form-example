[%bs.raw {|require('./App.css')|}];

module App = {
  let component = ReasonReact.statelessComponent("App");

  let make = _children => {
    ...component,
    render: _self =>
      <div className="App">
        <div className="container">
          <h2> (ReasonReact.string("Sign Up")) </h2>
          <SignupForm />
        </div>
      </div>,
  };
};

ReactDOMRe.renderToElementWithId(<App />, "root");