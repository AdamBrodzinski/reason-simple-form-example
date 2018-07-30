[%bs.raw {|require('./SimpleForm/SimpleForm.css')|}];
open SimpleForm;

let simulateServerResponse = formData =>
  Js.Promise.make((~resolve, ~reject) => {
    Js.log(formData);
    let _ = Js.Global.setTimeout(() => resolve(. formData), 1500);
    ();
  });

let component = ReasonReact.statelessComponent("SignupForm");

let isAge18AndUp = (inputState: SimpleForm_Types.inputState, _formState) => {
  let num = SimpleForm_Utils.intOfStringOrZero(inputState.value);
  let isValid = num >= 18;
  (isValid, "You must be over 18");
};

let formSchema: list(SimpleForm_Types.schemaItem) = [
  {name: "firstName", label: "First name", validations: [MinLen(2)]},
  {name: "age", label: "Age", validations: [Func(isAge18AndUp)]},
  {name: "income", label: "Income", validations: []},
  {name: "moreInfo", label: "More Info", validations: [MinLen(5)]},
  {name: "gender", label: "Gender", validations: [Required]},
  {name: "plan", label: "Plan", validations: [Required]},
  {name: "subscribe", label: "Subscribe to Newsletter", validations: []},
];

let make = _children => {
  let handleSubmit = (~sendLoaded, form: formState) =>
    if (form.isValid) {
      simulateServerResponse(form)
      |> Js.Promise.then_(_value => {
           sendLoaded();
           Js.Promise.resolve();
         })
      |> ignore;
    };

  {
    ...component,
    render: _self =>
      <div className="MyForm">
        <Form schema=formSchema onSubmit=handleSubmit debug=true>
          <TextInput name="firstName" />
          <IntInput name="age" />
          <FloatInput name="income" />
          <TextArea name="moreInfo" />
          <Radio
            name="gender"
            radioValues=[
              ("Male", "male"),
              ("Female", "female"),
              ("Trans", "trans"),
            ]
          />
          <Select
            name="plan"
            options=[
              ("Select Plan", ""),
              ("Bronze", "plan1"),
              ("Silver", "plan2"),
              ("Gold", "plan3"),
            ]
          />
          <Checkbox name="subscribe" />
          <Submit text="Update" />
        </Form>
      </div>,
  };
};