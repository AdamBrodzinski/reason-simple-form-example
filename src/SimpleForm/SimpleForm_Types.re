type validationResult = {
  isValid: bool,
  kind: string,
  message: string,
};

type inputState = {
  name: string,
  value: string,
  valid: bool,
  dirty: bool,
};

type formState = {
  submitted: bool,
  initialized: bool,
  inputStates: list(inputState),
};

/** used to validate an input using custom logic */
type validateFunc = (inputState, formState) => (bool, string);

type validations =
  | Required
  | Email
  | EmailWithMsg(string)
  | Regex(Js.Re.t, string)
  | Min(int)
  | Max(int)
  | Func(validateFunc);

/** Represents the schema for a single input */
type schemaItem = {
  name: string,
  label: string,
  validations: list(validations),
};

type context = {
  formState,
  schemas: list(schemaItem),
  updateInput: (string, string) => unit,
  sendInputBlur: string => unit,
};