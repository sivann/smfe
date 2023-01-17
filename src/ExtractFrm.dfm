object ExtractForm: TExtractForm
  Left = 212
  Top = 81
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'SMFE - Refreshing Gamelist Info'
  ClientHeight = 97
  ClientWidth = 293
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 78
    Height = 13
    Caption = 'Please wait...'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object ExLbl: TLabel
    Left = 8
    Top = 32
    Width = 210
    Height = 13
    Caption = '1. Extracting Game Info  (55 second timeout)'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object ParLbl: TLabel
    Left = 8
    Top = 56
    Width = 99
    Height = 13
    Caption = '2. Parsing Game Info'
  end
  object ProgressBar: TProgressBar
    Left = 0
    Top = 81
    Width = 293
    Height = 16
    Align = alBottom
    Min = 0
    Max = 3008
    TabOrder = 0
    Visible = False
  end
end
