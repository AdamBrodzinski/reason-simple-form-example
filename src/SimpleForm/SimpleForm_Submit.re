let component = ReasonReact.statelessComponent("SimpleForm_Submit");

let make = (~text="Submit", ~savingText="Saving...", ~isLoading=false, _ch) => {
  ...component,
  render: _self => {
    let buttonText = isLoading ? savingText : text;
    <div className="SimpleForm_Submit-container">
      <button type_="submit" className="SimpleForm_Submit" disabled=isLoading>
        (ReasonReact.string(buttonText))
      </button>
    </div>;
  },
};