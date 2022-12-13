#pragma once

class Event
{
    Event();

  public:

    using VoidFun = void();
    using IntFun = void(int value);
    using BoolFun = void(bool value);
    using CheckStateFun = void(Qt::CheckState value);
    using QStringFun = void(QString value);

    template <typename Widget> static void ButtonClicked(Widget w, std::function<VoidFun> callback);
    template <typename Widget> static void SpinBoxValueChanged(Widget w, std::function<IntFun> callback);
    template <typename Widget> static void LineEditTextChanged(Widget w, std::function<QStringFun> callback);
    template <typename Widget> static void PlainEditTextChanged(Widget w, std::function<QStringFun> callback);
    template <typename Widget> static void CheckBoxStateChanged(Widget w, std::function<IntFun> callback);
};

template <typename Widget> inline void Event::ButtonClicked(Widget w, std::function<VoidFun> callback)
{
    QObject::connect(w, &QPushButton::clicked, callback);
}
template <typename Widget>
inline void Event::SpinBoxValueChanged(Widget w, std::function<IntFun> callback)
{
    QObject::connect(w, &QSpinBox::textChanged, [callback, w](auto v) {
        callback(w->value());
    });
}

template <typename Widget> inline void Event::LineEditTextChanged(Widget w, std::function<QStringFun> callback)
{
    QObject::connect(w, &QLineEdit::textChanged, callback);
}

template <typename Widget> inline void Event::PlainEditTextChanged(Widget w, std::function<QStringFun> callback)
{
    QObject::connect(w, &QPlainTextEdit::textChanged, [callback, w]() { callback(w->toPlainText()); });
}

template <typename Widget> inline void Event::CheckBoxStateChanged(Widget w, std::function<IntFun> callback)
{
    QObject::connect(w, &QCheckBox::stateChanged, callback);
}
