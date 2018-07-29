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
      ~radioValues,
      ~idPrefix="SF_",
      ~unsafeProps=?,
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
                 /* container div catches change events */
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
                     radioValues
                     |> List.mapi((i, (label, value)) =>
                          <label
                            className="SimpleForm_Radio-label"
                            key=(string_of_int(i))
                            htmlFor=(idPrefix ++ value)>
                            {
                              let input =
                                <input
                                  id=(idPrefix ++ value)
                                  type_="radio"
                                  value
                                  name
                                />;

                              switch (unsafeProps) {
                              | Some(props) =>
                                ReasonReact.cloneElement(input, ~props, [||])
                              | None => ReasonReact.cloneElement(input, [||])
                              };
                            }
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