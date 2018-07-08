type schemaItem = {
  name: string,
  label: string,
};

type inputState = {
  name: string,
  value: string,
  dirty: bool,
};

type formState = {
  submitted: bool,
  initialized: bool,
  inputStates: list(inputState),
};

type context = {
  formState,
  schemas: list(schemaItem),
  updateInput: (string, string) => unit,
};