open SimpleForm_Types;

type formEv = ReactEventRe.Form.t;

/** print out contents and then return it */
let inspect = x => {
  Js.log(x);
  x;
};

/** handy function to map over data and return a react array */
let mapReactList = (elList, func) =>
  List.mapi(func, elList) |> Array.of_list |> ReasonReact.array;

let getEventValue = (event: formEv) => {
  let target = ReactEventRe.Form.target(event);
  ReactDOMRe.domElementToObj(target)##value;
};

let getEventIsChecked = (event: formEv) : bool => {
  let target = ReactEventRe.Form.target(event);
  ReactDOMRe.domElementToObj(target)##checked;
};

let preventDefault = (event: formEv) =>
  ReactEventRe.Form.preventDefault(event);

let findSchemaByName = (schemas, name) =>
  List.find((x: schemaItem) => x.name == name, schemas);

let findStateByName = (formStates, name) =>
  List.find((x: inputState) => x.name == name, formStates);

/* used for optional react props */
let fallbackFunc = (optionFunc, defaultFunc) =>
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

/**  Determine if a string will parse into a
     Float without throwing an exception
 */
let isStringFloat = value =>
  switch (float_of_string(value)) {
  | _num => true
  | exception (Failure("float_of_string")) => false
  };

/**  Determine if a string will parse into a
     Bool without throwing an exception
 */
let isStringBool = value =>
  switch (bool_of_string(value)) {
  | _num => true
  | exception (Failure("bool_of_string")) => false
  };

/** parses an int but provides a default for empty string */
let intOfStringOrZero = (x: string) =>
  switch (String.trim(x)) {
  | "" => 0
  | num => int_of_string(num)
  };

let insertProps = (unsafeProps, input) =>
  switch (unsafeProps) {
  | Some(props) => ReasonReact.cloneElement(input, ~props, [||])
  | None => ReasonReact.cloneElement(input, [||])
  };

type fieldMetadata = {
  ctx: context,
  state: inputState,
  inputSchema: schemaItem,
  hasSubmitted: bool,
  sendBlur: unit => unit,
  sendChange: string => unit,
};

let inputApi = (name: string, consumerFun, ctx) =>
  /* context will always render once with empty data, prev empty render */
  switch (List.length(ctx.schemas) > 0) {
  | false => ReasonReact.null
  | true =>
    let inputStates = ctx.formState.inputStates;
    consumerFun({
      ctx,
      state: findStateByName(inputStates, name),
      inputSchema: findSchemaByName(ctx.schemas, name),
      hasSubmitted: ctx.formState.submitted,
      sendBlur: () => ctx.sendInputBlur(name),
      sendChange: value => ctx.updateInput(name, value),
    });
  };