[%bs.raw {|require('./SimpleForm/SimpleForm.css')|}];
open SimpleForm;

type state = {loading: bool};

type action =
  | Loading
  | Loaded;

let component = ReasonReact.reducerComponent("MyForm");

let age18AndUp = (inputState: SimpleForm_Types.inputState, _formState) => {
  let num = SimpleForm_Utils.intOfStringOrZero(inputState.value);
  let isValid = num >= 18;
  (isValid, "You must be over 18");
};

let formSchema: list(SimpleForm_Types.schemaItem) = [
  {name: "firstName", label: "First name", validations: [MinLen(2)]},
  {name: "lastName", label: "Last name", validations: [MinLen(2)]},
  {name: "age", label: "Age", validations: [Func(age18AndUp)]},
];

let make = _children => {
  let handleSubmit = (formState: SimpleForm_Types.formState, self) => {
    Js.log("Submit form");
    Js.log(formState.inputStates |> Array.of_list);
    self.ReasonReact.send(Loaded);
  };

  {
    ...component,
    initialState: () => {loading: false},
    reducer: (action, _state) =>
      switch (action) {
      | Loading => ReasonReact.Update({loading: true})
      | Loaded => ReasonReact.Update({loading: false})
      },
    render: self =>
      <div className="MyForm">
        <Form schema=formSchema onSubmit=(self.handle(handleSubmit))>
          <TextInput name="firstName" />
          <TextInput name="lastName" beforeUpdate=String.lowercase />
          <IntInput name="age" />
          <Submit text="Update" isLoading=self.state.loading />
        </Form>
      </div>,
  };
};