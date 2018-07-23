open SimpleForm_Types;
module U = SimpleForm_Utils;

let component = ReasonReact.statelessComponent("SimpleForm_TextArea");

let handleChange = (ctx, name, value) : unit => ctx.updateInput(name, value);

let handleBlur = (ctx, name, _event) => ctx.sendInputBlur(name);

let make = (~name: string, ~unsafeProps=?, ~beforeUpdate=?, _ch) => {
  ...component,
  render: _self =>
    <SimpleForm_Form.Context.Consumer>
      ...(
           ctx =>
             if (List.length(ctx.schemas) > 0) {
               let inputStates = ctx.formState.inputStates;
               let inputSchema = U.findSchemaByName(ctx.schemas, name);
               let inputState = U.findStateByName(inputStates, name);
               let hasSubmitted = ctx.formState.submitted;

               let textArea =
                 <textarea
                   name
                   value=inputState.value
                   onBlur=(handleBlur(ctx, name))
                   onChange=(
                     event => {
                       let value: string = U.getEventValue(event);
                       let beforeUpdate = U.fallbackFunc(beforeUpdate, x => x);
                       let value2 = beforeUpdate(value);
                       handleChange(ctx, name, value2);
                     }
                   )
                 />;

               <div className="SimpleForm_TextArea-container">
                 <label> (ReasonReact.string(inputSchema.label)) </label>
                 <SimpleForm_ErrorMsg
                   inputState
                   hasSubmitted
                   errors=inputState.errors
                 />
                 (
                   switch (unsafeProps) {
                   | Some(props) =>
                     ReasonReact.cloneElement(textArea, ~props, [||])
                   | None => ReasonReact.cloneElement(textArea, [||])
                   }
                 )
               </div>;
             } else {
               ReasonReact.null;
             }
         )
    </SimpleForm_Form.Context.Consumer>,
};