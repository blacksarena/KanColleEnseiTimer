depends on
`$sudo apt-get install wmctrl`

change icon(for Unity desltop)
1. desktop file
    $cd ~/.local/share/applications/
    $nano kancolleenseitimer.desktop (create or edit)

>kancolleenseitimer.desktop
>[Desktop Entry]
>Encoding=UTF-8
>Version=1.0
>Type=Application
>Name=KanColleEnseiTimer
>Icon=<your home path>/.local/share/icons/kancolleenseitimer/icon.png
>Path=<your home path>/KanColleEnseiTimer
>Exec=<your home path>/KanColleEnseiTimer/KanColleEnseiTimer
>StartupNotify=false
>StartupWMClass=KanColleEnseiTimer
>OnlyShowIn=Unity;
>X-UnityGenerated=true

save and exit.

2. copy icon to save locale
    $cd ~/.local/share/icons/
    $mkdir kancolleenseitimer
    $cp ~/KanColleEnseiTimer/icons/icon.png icon.png

3. reboot
