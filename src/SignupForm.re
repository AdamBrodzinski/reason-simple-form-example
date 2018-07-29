[%bs.raw {|require('./SimpleForm/SimpleForm.css')|}];
open SimpleForm;

let simulateServerResponse = formData =>
  Js.Promise.make((~resolve, ~reject) => {
    Js.log(formData);
    let _ = Js.Global.setTimeout(() => resolve(. formData), 1500);
    ();
  });

type state = {loading: bool};

type action =
  | Loading
  | Loaded;

let component = ReasonReact.reducerComponent("SignupForm");

let age18AndUp = (inputState: SimpleForm_Types.inputState, _formState) => {
  let num = SimpleForm_Utils.intOfStringOrZero(inputState.value);
  let isValid = num >= 18;
  (isValid, "You must be over 18");
};

let formSchema: list(SimpleForm_Types.schemaItem) = [
  {name: "firstName", label: "First name", validations: [MinLen(2)]},
  {name: "age", label: "Age", validations: [Func(age18AndUp)]},
  {name: "moreInfo", label: "More Info", validations: [MinLen(5)]},
  {name: "gender", label: "Gender", validations: [Required]},
];

let make = _children => {
  let handleSubmit = (formState: SimpleForm_Types.formState, self) =>
    if (formState.isValid) {
      self.ReasonReact.send(Loading);
      Js.log("sending form values to fake server...");
      simulateServerResponse(formState)
      |> Js.Promise.then_(_value => {
           self.ReasonReact.send(Loaded);
           Js.log("Save successful");
           Js.Promise.resolve();
         })
      |> ignore;
    } else {
      Js.log("do nothing, user will see visual errors");
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
        <Form
          schema=formSchema onSubmit=(self.handle(handleSubmit)) debug=false>
          <TextInput name="firstName" />
          <IntInput name="age" />
          <TextArea name="moreInfo" />
          <Radio
            name="gender"
            radioValues=[
              ("Male", "male"),
              ("Female", "female"),
              ("Trans", "trans"),
            ]
          />
          <Submit text="Update" isLoading=self.state.loading />
        </Form>
      </div>,
  };
};