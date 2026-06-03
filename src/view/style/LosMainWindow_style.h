#pragma once

#include <string>

namespace LosView
{
namespace LosMainWindow_style
{

inline std::string getStyle()
{
    return R"(
QMainWindow,
QWidget#centralWidget {
    background: #050505;
    color: #ffffff;
    font-family: "Microsoft YaHei", "Noto Sans CJK SC", "Segoe UI", sans-serif;
    font-size: 14px;
}

QFrame#headerFrame {
    background: #0c0c0c;
    border: 1px solid #2a2a2a;
    border-left: 4px solid #c40022;
    border-radius: 14px;
}

QLabel {
    color: #ffffff;
    font-family: "Microsoft YaHei", "Noto Sans CJK SC", "Segoe UI", sans-serif;
    font-size: 14px;
}

QLabel#titleLabel {
    color: #ffffff;
    font-size: 28px;
    font-weight: 900;
    letter-spacing: 1px;
}

QLabel#subtitleLabel,
QLabel#footerLabel {
    color: #cfcfcf;
    font-size: 13px;
}

QGroupBox {
    background: #0d0d0d;
    border: 1px solid #2b2b2b;
    border-radius: 14px;
    margin-top: 14px;
    padding-top: 10px;
    color: #ffffff;
    font-size: 15px;
    font-weight: 800;
}

QGroupBox::title {
    subcontrol-origin: margin;
    subcontrol-position: top left;
    left: 18px;
    padding: 0 10px;
    color: #ff193d;
    background: #0d0d0d;
}

QFrame#topContentFrame,
QFrame#rightPanelFrame {
    background: transparent;
}

QListWidget,
QTextEdit,
QLineEdit {
    background: #ffffff;
    color: #111111;
    border: 2px solid #202020;
    border-radius: 10px;
    padding: 8px;
    selection-background-color: #c40022;
    selection-color: #ffffff;
    font-family: "Microsoft YaHei", "Noto Sans CJK SC", "Segoe UI", sans-serif;
    font-size: 14px;
}

QListWidget::item {
    min-height: 28px;
    padding: 6px 10px;
    border-radius: 7px;
    color: #111111;
}

QListWidget::item:hover {
    background: #f1f1f1;
}

QListWidget::item:selected {
    background: #c40022;
    color: #ffffff;
}

QLineEdit {
    min-height: 34px;
}

QLineEdit:focus,
QTextEdit:focus,
QListWidget:focus {
    border: 2px solid #ff193d;
}

QLineEdit::placeholder {
    color: #777777;
}

QPushButton {
    background: #ffffff;
    color: #0b0b0b;
    border: 2px solid #ffffff;
    border-radius: 10px;
    padding: 7px 14px;
    min-height: 32px;
    font-weight: 800;
    font-family: "Microsoft YaHei", "Noto Sans CJK SC", "Segoe UI", sans-serif;
    font-size: 14px;
}

QPushButton:hover {
    background: #f1f1f1;
    border-color: #ff193d;
    color: #c40022;
}

QPushButton:pressed {
    background: #c40022;
    border-color: #c40022;
    color: #ffffff;
}

QPushButton:disabled {
    background: #252525;
    border-color: #333333;
    color: #777777;
}

QPushButton#startButton {
    background: #c40022;
    border-color: #ff193d;
    color: #ffffff;
}

QPushButton#startButton:hover {
    background: #ff193d;
    border-color: #ffffff;
    color: #ffffff;
}

QCheckBox {
    spacing: 10px;
    color: #ffffff;
    font-weight: 700;
    font-family: "Microsoft YaHei", "Noto Sans CJK SC", "Segoe UI", sans-serif;
    font-size: 14px;
}

QCheckBox::indicator {
    width: 18px;
    height: 18px;
    border-radius: 5px;
    border: 2px solid #ffffff;
    background: #050505;
}

QCheckBox::indicator:hover {
    border-color: #ff193d;
}

QCheckBox::indicator:checked {
    background: #c40022;
    border-color: #ff193d;
}

QLabel#summaryLabel {
    background: #ffffff;
    color: #0b0b0b;
    border: 2px solid #c40022;
    border-radius: 12px;
    padding: 10px 12px;
    font-size: 15px;
    font-weight: 900;
}

QLabel#targetHintLabel {
    color: #d0d0d0;
}

QProgressBar {
    background: #ffffff;
    border: 2px solid #202020;
    border-radius: 10px;
    min-height: 20px;
    text-align: center;
    color: #111111;
    font-weight: 900;
}

QProgressBar::chunk {
    border-radius: 7px;
    background: #c40022;
}

QSplitter::handle:vertical {
    background: #202020;
    height: 8px;
    border-radius: 4px;
}

QSplitter::handle:vertical:hover {
    background: #c40022;
}

QScrollBar:vertical {
    background: #ffffff;
    width: 12px;
    border-radius: 6px;
}

QScrollBar::handle:vertical {
    background: #111111;
    border-radius: 6px;
    min-height: 30px;
}

QScrollBar::handle:vertical:hover {
    background: #c40022;
}

QScrollBar::add-line:vertical,
QScrollBar::sub-line:vertical {
    height: 0px;
}

QScrollBar:horizontal {
    background: #ffffff;
    height: 12px;
    border-radius: 6px;
}

QScrollBar::handle:horizontal {
    background: #111111;
    border-radius: 6px;
    min-width: 30px;
}

QScrollBar::handle:horizontal:hover {
    background: #c40022;
}

QScrollBar::add-line:horizontal,
QScrollBar::sub-line:horizontal {
    width: 0px;
}
)";
}

inline std::string GetDirectoryDialogStyle()
{
    return R"(
QFileDialog {
    background: #101010;
    color: #ffffff;
    font-family: "Microsoft YaHei", "Noto Sans CJK SC", "Segoe UI", sans-serif;
    font-size: 14px;
}

QFileDialog QWidget {
    background: #101010;
    color: #ffffff;
}

QFileDialog QLabel {
    color: #ffffff;
}

QFileDialog QTreeView,
QFileDialog QListView,
QFileDialog QTableView {
    background: #ffffff;
    color: #111111;
    border: 1px solid #333333;
    selection-background-color: #c40022;
    selection-color: #ffffff;
    alternate-background-color: #f5f5f5;
}

QFileDialog QHeaderView::section {
    background: #f1f1f1;
    color: #111111;
    border: 1px solid #d0d0d0;
    padding: 5px 8px;
}

QFileDialog QLineEdit,
QFileDialog QComboBox {
    background: #ffffff;
    color: #111111;
    border: 1px solid #555555;
    border-radius: 7px;
    padding: 5px 8px;
    min-height: 28px;
}

QFileDialog QComboBox QAbstractItemView {
    background: #ffffff;
    color: #111111;
    selection-background-color: #c40022;
    selection-color: #ffffff;
}

QFileDialog QPushButton {
    background: #ffffff;
    color: #111111;
    border: 1px solid #555555;
    border-radius: 8px;
    padding: 6px 14px;
    min-height: 30px;
    font-weight: 800;
}

QFileDialog QPushButton:hover {
    background: #f1f1f1;
    border-color: #ff193d;
    color: #c40022;
}

QFileDialog QPushButton:pressed {
    background: #c40022;
    border-color: #c40022;
    color: #ffffff;
}

QFileDialog QScrollBar:vertical {
    background: #ffffff;
    width: 12px;
}

QFileDialog QScrollBar::handle:vertical {
    background: #111111;
    border-radius: 6px;
    min-height: 30px;
}

QFileDialog QScrollBar::handle:vertical:hover {
    background: #c40022;
}

QFileDialog QScrollBar::add-line:vertical,
QFileDialog QScrollBar::sub-line:vertical {
    height: 0px;
}
)";
}

}
}
