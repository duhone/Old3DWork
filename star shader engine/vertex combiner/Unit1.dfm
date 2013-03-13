object Form1: TForm1
  Left = 295
  Top = 130
  Width = 611
  Height = 426
  Caption = 'Vertex Combiner'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 120
  TextHeight = 16
  object StatusBar: TStatusBar
    Left = 0
    Top = 362
    Width = 603
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object vertex_shaders: TListBox
    Left = 0
    Top = 0
    Width = 603
    Height = 362
    Hint = 'Right Click to Add/Remove/Build'
    Align = alClient
    ItemHeight = 16
    ParentShowHint = False
    PopupMenu = PopupMenu1
    ShowHint = True
    TabOrder = 1
  end
  object PopupMenu1: TPopupMenu
    Left = 184
    Top = 8
    object InsertFile1: TMenuItem
      Caption = 'Insert File'
      OnClick = InsertFile1Click
    end
    object DeleteFile1: TMenuItem
      Caption = 'Delete File'
      OnClick = DeleteFile1Click
    end
    object Build1: TMenuItem
      Caption = 'Build'
      OnClick = Build1Click
    end
  end
  object OpenFile: TOpenDialog
    DefaultExt = '.txt'
    Filter = 'Vertex Shader|*.dsf'
    Title = 'Insert Vertex Shader'
    Left = 184
    Top = 40
  end
  object SaveFile: TSaveDialog
    Left = 184
    Top = 72
  end
end
