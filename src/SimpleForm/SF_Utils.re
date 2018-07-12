open SF_Types;
type formEv = ReactEventRe.Form.t;

/** print out contents and then return it */
let inspect = x => {
  Js.log(x);
  x;
};

let getEventValue = (event: formEv) => {
  let target = ReactEventRe.Form.target(event);
  ReactDOMRe.domElementToObj(target)##value;
};

let preventDefault = (event: formEv) =>
  ReactEventRe.Form.preventDefault(event);

let findSchemaByName = (schemas, name) =>
  List.find((x: SF_Types.schemaItem) => x.name == name, schemas);

let findStateByName = (formStates, name) =>
  List.find((x: SF_Types.inputState) => x.name == name, formStates);

/* used for optional react props */
let maybeFunc = (optionFunc, defaultFunc) =>
  switch (optionFunc) {
  | Some(fn) => fn
  | None => defaultFunc
  };

/**  Determine if a string will parse into an
     Int without throwing an exception
 */
let isStringInteger = value =>
  switch (int_of_string(value)) {
  | _num => true
  | exception (Failure("int_of_string")) => false
  };

/* validations */

let validateRequired = (iState: inputState, iSchema: schemaItem) => {
  let isValid = iState.value |> String.trim |> String.length > 0;
  {isValid, kind: "required", message: "This field is required"};
};

let validateInput = (iSchema: schemaItem, iState: inputState) =>
  switch (iSchema.validations) {
  | [] => []
  | _ =>
    iSchema.validations
    |> List.map(validateVariant =>
         switch (validateVariant) {
         | Required => validateRequired(iState, iSchema)
         | Email => validateRequired(iState, iSchema)
         }
       )
  };

let inputIsValid = (iSchema, iState) =>
  validateInput(iSchema, iState)
  |> inspect
  |> List.filter(v => v.isValid == false)
  |> List.length == 0;