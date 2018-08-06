open SimpleForm_Types;
module U = SimpleForm_Utils;

exception InvalidInputCastType(string);

let excMsg =
  "It seems you have passed in a `Bool castType into an Input."
  ++ "Please use a castType of `String, `Float, or `Int instead.";

let component = ReasonReact.statelessComponent("SimpleForm_Input");

let make = (~name: string, ~unsafeProps=?, ~beforeUpdate=?, _ch) => {
  ...component,
  render: _self =>
    <SimpleForm_Form.Context.Consumer>
      ...(
           ctx =>
             if (List.length(ctx.schemas) > 0) {
               let inputSchema = U.findSchemaByName(ctx.schemas, name);
               switch (inputSchema.castType) {
               | `String =>
                 <SimpleForm_TextInput name ?unsafeProps ?beforeUpdate />
               | `Float =>
                 <SimpleForm_FloatInput name ?unsafeProps ?beforeUpdate />
               | `Int =>
                 <SimpleForm_IntInput name ?unsafeProps ?beforeUpdate />
               | `Bool => raise(InvalidInputCastType(excMsg))
               };
             } else {
               ReasonReact.null;
             }
         )
    </SimpleForm_Form.Context.Consumer>,
};