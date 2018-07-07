open SF_Types;
module U = SF_Utils;

type formEvent = ReactEventRe.Form.t;
type beforeFn = option(string => string);

let component = ReasonReact.statelessComponent("SF_IntInput");

let handleChange = (ctx, name, beforeUpdate, event: formEvent) => {
  let value = U.getEventValue(event);
  let value2 = beforeUpdate(value);
  if (value2 == "" || U.isStringInteger(value2)) {
    ctx.updateInput(name, value2);
  };
};

let make = (~name: string, ~unsafeProps=?, ~beforeUpdate: beforeFn=?, _ch) => {
  ...component,
  render: _self =>
    <SF_Form.Context.Consumer>
      ...(
           ctx => {
             let schema = U.findSchemaByName(ctx.schemas, name);
             let state = U.findStateByName(ctx.formState.inputStates, name);
             let beforeUpdate = U.maybeFunc(beforeUpdate, x => x);
             <div className="SF_IntInput-container">
               <label> (ReasonReact.string(schema.label)) </label>
               <SF_Input
                 name
                 type_="text"
                 value=state.value
                 unsafeProps
                 onChange=(handleChange(ctx, name, beforeUpdate))
               />
             </div>;
           }
         )
    </SF_Form.Context.Consumer>,
};