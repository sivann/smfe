object HelpFrm: THelpFrm
  Left = 498
  Top = 104
  Width = 435
  Height = 230
  BorderIcons = [biSystemMenu]
  Caption = 'Getting Started'
  Color = clBtnFace
  Constraints.MinWidth = 435
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object HelpMemo: TMemo
    Left = 0
    Top = 0
    Width = 427
    Height = 203
    Align = alClient
    BorderStyle = bsNone
    Color = 12639424
    Lines.Strings = (
      'Quick startup info for the impatient:'
      '------------------------------------'
      
        '1. Go to menu "Settings->Edit SMFE Paths" and fill in MAME'#39's (ex' +
        'ecutable) path'
      
        '2. Run "Game Data->Read Gamelist from mame" to read mame'#39's suppo' +
        'rted'
      '   games.'
      ''
      'optionally:'
      ''
      '*  Select "ROMs->ROM Availability" (fast) or'
      
        '   "ROMs->ROM Availability && Verification" (accurate but slow) ' +
        'to see'
      '   which roms are available at your system'
      ''
      
        '*  If for example mame.exe is in the directory "mamedir" and rom' +
        's are not'
      '   inside "mamedir/roms"'
      
        '   you must select the roms directory in menu "Settings->Edit MA' +
        'ME Options"'
      ''
      ' ')
    ScrollBars = ssBoth
    TabOrder = 0
  end
end
