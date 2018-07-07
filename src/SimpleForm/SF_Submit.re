let component = ReasonReact.statelessComponent("MyForm");

let make = (~text, _children) => {
  ...component,
  render: _self =>
    <div className="SF_Submit-container">
      <button type_="submit" className="SF_Submit">
        (ReasonReact.string(text))
      </button>
    </div>,
};