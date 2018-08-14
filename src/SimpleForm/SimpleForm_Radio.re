open SimpleForm_Types;
module U = SimpleForm_Utils;

let component = ReasonReact.statelessComponent("SimpleForm_Radio");

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
           SimpleForm_Utils.inputApi(
             name, ({state, inputSchema, hasSubmitted, sendBlur, sendChange}) =>
             <div className="SimpleForm_Radio-container">
               <label> (ReasonReact.string(inputSchema.label)) </label>
               <SimpleForm_ErrorMsg inputState=state hasSubmitted />
               /* container div catches change events */
               <div
                 onChange=(
                   event => {
                     let value: string = U.getEventValue(event);
                     let beforeUpdate = U.fallbackFunc(beforeUpdate, x => x);
                     let value2 = beforeUpdate(value);
                     sendChange(value2);
                     sendBlur();
                   }
                 )>
                 (
                   radioValues
                   |> List.mapi((i, (label, value)) =>
                        <label
                          className="SimpleForm_Radio-label"
                          key=(string_of_int(i))
                          htmlFor=(idPrefix ++ value)>
                          (
                            <input
                              id=(idPrefix ++ value)
                              type_="radio"
                              value
                              name
                            />
                            |> U.insertProps(unsafeProps)
                          )
                          (ReasonReact.string(label))
                        </label>
                      )
                   |> Array.of_list
                   |> ReasonReact.array
                 )
               </div>
             </div>
           )
         )
    </SimpleForm_Form.Context.Consumer>,
};