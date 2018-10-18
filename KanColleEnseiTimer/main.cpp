#include "mainwindow.h"
#include <QApplication>
#include <pcap.h>

void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
    printf("packet_length: %d\n", header->len);
    printf("packet: %s\n", packet);
}

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    pcap_t *handle = NULL;
    char err[256];
    char *dev = pcap_lookupdev(err);
    if (dev == NULL) {
        printf("デフォルトのディバイスを発見できませんでした: %s\n", err);
    }else{
        printf("device: %s\n", dev);
    }

    handle = pcap_open_live(dev, 2048, true, 10000, err);
    if(handle == NULL){
        printf("device[%s] cant open: %s\n", dev, err);
        return -1;
    }else{
        printf("device open\n");
    }

    struct bpf_program fp;
    char filter_exp[] = "port 80 and http";
    //char filter_exp[] = "tcp port 80 and (((ip[2:2] - ((ip[0]&0xf)<<2)) - ((tcp[12]&0xf0)>>2)) != 0)";
    bpf_u_int32 net;
    if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
        printf("フィルタ「%s」を解析できませんでした: %s\n", filter_exp, pcap_geterr(handle));
    }

    if (pcap_setfilter(handle, &fp) == -1) {
        printf("フィルタ「%s」の組み込みができませんでした: %s\n", filter_exp, pcap_geterr(handle));
    }

    const u_char *packet = 0;
    struct pcap_pkthdr header;
    int cnt = -1;
    pcap_loop(handle, cnt, got_packet, NULL);

    //packet = pcap_next(handle, &header);
    //printf("packet: %s\n", packet);

    return 0;//a.exec();
}
