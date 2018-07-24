open SimpleForm_Types;
module U = SimpleForm_Utils;

let component = ReasonReact.statelessComponent("SimpleForm_TextArea");

let handleChange = (ctx, name, value) : unit => {
  ctx.updateInput(name, value);
  /* send blur to trigger a 'dirty' state */
  ctx.sendInputBlur(name);
};

let make =
    (
      ~name: string,
      ~radioInputs,
      ~idPrefix="SF_",
      ~unsafeProps={"name": name},
      ~beforeUpdate=?,
      _ch,
    ) => {
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

               <div className="SimpleForm_Radio-container">
                 <label> (ReasonReact.string(inputSchema.label)) </label>
                 <SimpleForm_ErrorMsg
                   inputState
                   hasSubmitted
                   errors=inputState.errors
                 />
                 <div
                   onChange=(
                     event => {
                       let value: string = U.getEventValue(event);
                       let beforeUpdate = U.fallbackFunc(beforeUpdate, x => x);
                       let value2 = beforeUpdate(value);
                       handleChange(ctx, name, value2);
                     }
                   )>
                   (
                     radioInputs
                     |> List.mapi((i, (label, value)) =>
                          <label
                            className="SimpleForm_Radio-label"
                            key=(string_of_int(i))
                            htmlFor=(idPrefix ++ value)>
                            <input
                              id=(idPrefix ++ value)
                              type_="radio"
                              value
                              name
                            />
                            (ReasonReact.string(label))
                          </label>
                        )
                     |> Array.of_list
                     |> ReasonReact.array
                   )
                 </div>
               </div>;
             } else {
               ReasonReact.null;
             }
         )
    </SimpleForm_Form.Context.Consumer>,
};