let component = ReasonReact.statelessComponent("MyForm");

let make = (~text="Submit", ~savingText="Saving...", ~isLoading, _ch) => {
  ...component,
  render: _self => {
    let btnType = isLoading ? "button" : "submit";
    let btnText = isLoading ? savingText : text;
    <div className="SF_Submit-container">
      <button type_=btnType className="SF_Submit">
        (ReasonReact.string(btnText))
      </button>
    </div>;
  },
};