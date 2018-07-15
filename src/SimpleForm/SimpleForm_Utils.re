module T = SimpleForm_Types;

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
  List.find((x: T.schemaItem) => x.name == name, schemas);

let findStateByName = (formStates, name) =>
  List.find((x: T.inputState) => x.name == name, formStates);

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