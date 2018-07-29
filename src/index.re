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
          <br />
          <div>
            <h4>
              <a
                href="https://github.com/AdamBrodzinski/reason-simple-form-example">
                (ReasonReact.string("reason-simple-form-example Repo"))
              </a>
            </h4>
          </div>
        </div>
      </div>,
  };
};

ReactDOMRe.renderToElementWithId(<App />, "root");