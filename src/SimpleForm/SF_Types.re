/** used to validate an input using custom logic */
type validateFunc = string => bool;

type validations =
  | Required;
/* | Email
   | Min(int)
   | Max(int); */

/** Represents the schema for a single input */
type schemaItem = {
  name: string,
  label: string,
  validations: list(validations),
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

type context = {
  formState,
  schemas: list(schemaItem),
  updateInput: (string, string) => unit,
};