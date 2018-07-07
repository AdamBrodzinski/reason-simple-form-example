type formEv = ReactEventRe.Form.t;

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