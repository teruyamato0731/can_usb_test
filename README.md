# can_usb_test
CAN-USB を使用して Ubuntu の USB から CAN を読み取る。
Ubuntu 22.04 で動作の確認を行った。

# How to use
1. `sudo modprobe can` で CAN を有効化.
1. `ip link show type can` で CAN インターフェイスを確認.
1. CAN インターフェイスの bitrate を設定し, 立ち上げる.
    例は CAN インターフェイスが can0 だった場合を示している.
    ```bash
    # bitrate を 1Mbps に設定
    sudo ip link set can0 type can bitrate 1000000
    # 500kbps ならこちら
    # sudo ip link set can0 type can bitrate 500000
    # 立ち上げる
    sudo ip link set can0
    # 止める
    # sudo ip link set can0 down
    ```
1. CAN を受信しているか確認する場合, can-utils の candump を使用することもできる
    ```bash
    sudo apt install can-utils
    candump can0
    ```
1. ビルドして実行
    ```bash
    (cd can_read && gcc main.c -o can_read.out && ./can_read.out)
    (cd can_send && gcc main.c -o can_send.out && ./can_send.out)
    ```

# 参考
- https://tech.aptpod.co.jp/entry/2021/06/18/100000
- https://qiita.com/yuichi-kusakabe/items/e5b50aa3edb712bb6916
- https://docs.kernel.org/networking/can.html
- https://en.wikipedia.org/wiki/SocketCAN
- https://github.com/linux-can/can-utils
