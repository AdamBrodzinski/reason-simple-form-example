let component = ReasonReact.statelessComponent("SimpleForm_Submit");

let make =
    (
      ~text="Submit",
      ~savingText="Saving...",
      ~errorText="Please fix errors in red and try again",
      _ch,
    ) => {
  ...component,
  render: _self =>
    <SimpleForm_Form.Context.Consumer>
      ...(
           ctx =>
             if (List.length(ctx.schemas) > 0) {
               let state = ctx.formState;
               let buttonText = state.loading ? savingText : text;
               let errorText =
                 ! state.isValid && state.submitted ? errorText : "";
               <div className="SimpleForm_Submit-container">
                 <div className="SimpleForm_ErrorMsg">
                   (ReasonReact.string(errorText))
                 </div>
                 <button
                   type_="submit"
                   className="SimpleForm_Submit"
                   disabled=ctx.formState.loading>
                   (ReasonReact.string(buttonText))
                 </button>
               </div>;
             } else {
               ReasonReact.null;
             }
         )
    </SimpleForm_Form.Context.Consumer>,
};