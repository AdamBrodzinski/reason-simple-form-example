let component = ReasonReact.statelessComponent("SimpleForm_Submit");

let make = (~text="Submit", ~savingText="Saving...", ~isLoading=false, _ch) => {
  ...component,
  render: _self => {
    let btnType = isLoading ? "button" : "submit";
    let btnText = isLoading ? savingText : text;
    <div className="SimpleForm_Submit-container">
      <button type_=btnType className="SimpleForm_Submit">
        (ReasonReact.string(btnText))
      </button>
    </div>;
  },
};