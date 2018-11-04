let component = ReasonReact.statelessComponent("Index");

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <Next.Head>
        <script
          src="//www.gstatic.com/cast/sdk/libs/caf_receiver/v3/cast_receiver_framework.js"
        />
      </Next.Head>
      <GameView />
    </div>,
};

let default = ReasonReact.wrapReasonForJs(~component, _jsProps => make([||]));