open SimpleForm_Types;
module U = SimpleForm_Utils;

let component = ReasonReact.statelessComponent("SimpleForm_Select");

let handleChange = (ctx, name, value) : unit => {
  ctx.updateInput(name, value);
  /* send blur to trigger a 'dirty' state */
  ctx.sendInputBlur(name);
};

let make = (~name: string, ~options, ~unsafeProps=?, ~beforeUpdate=?, _ch) => {
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

               <div className="SimpleForm_Select-container">
                 <label> (ReasonReact.string(inputSchema.label)) </label>
                 <SimpleForm_ErrorMsg
                   inputState
                   hasSubmitted
                   errors=inputState.errors
                 />
                 {
                   let input =
                     <select
                       className="SimpleForm_Select"
                       onChange=(
                         event => {
                           let value: string = U.getEventValue(event);
                           let beforeUpdate =
                             U.fallbackFunc(beforeUpdate, x => x);
                           let value2 = beforeUpdate(value);
                           handleChange(ctx, name, value2);
                         }
                       )>
                       (
                         List.mapi(
                           (i, (label, value)) =>
                             <option
                               className="SimpleForm_Select-option"
                               key=(string_of_int(i))
                               value>
                               (ReasonReact.string(label))
                             </option>,
                           options,
                         )
                         |> Array.of_list
                         |> ReasonReact.array
                       )
                     </select>;

                   switch (unsafeProps) {
                   | Some(props) =>
                     ReasonReact.cloneElement(input, ~props, [||])
                   | None => ReasonReact.cloneElement(input, [||])
                   };
                 }
               </div>;
             } else {
               ReasonReact.null;
             }
         )
    </SimpleForm_Form.Context.Consumer>,
};