# Copyright 2015 University of Rochester
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
# http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License. 


library(plyr)
library(ggplot2)

scientific_10 <- function(x) {
  parse(text=gsub("1e\\+", "10^", scales::scientific_format()(x)))
}
tests<-c("g50i25r25_size")
for (t in tests){
read.csv(paste("./maps_",t,".csv",sep=""))->montagedata

montagedata$ds<-as.factor(gsub("NoPersistTransientHashTable<DRAM>","DRAM (T)",montagedata$ds))
montagedata$ds<-as.factor(gsub("NoPersistTransientHashTable<NVM>","NVM (T)",montagedata$ds))
montagedata$ds<-as.factor(gsub("NoPersistMontageHashTable","Montage (T)",montagedata$ds))
montagedata$ds<-as.factor(gsub("MontageHashTable","Montage",montagedata$ds))
montagedata$ds<-as.factor(gsub("NoPersistDali","Dalí",montagedata$ds))
montagedata$ds<-as.factor(gsub("NoPersistSOFT","SOFT",montagedata$ds))
montagedata$ds<-as.factor(gsub("NoPersistMODHashTable","MOD",montagedata$ds))
montagedata$ds<-as.factor(gsub("NoPersistMneHashTable","Mnemosyne",montagedata$ds))
montagedata$ds<-as.factor(gsub("SyncNoPersistProntoHashTable","Pronto-Sync",montagedata$ds))
montagedata$ds<-as.factor(gsub("FullNoPersistProntoHashTable","Pronto-Full",montagedata$ds))
montagedata$ds<-as.factor(gsub("NoPersistNVTraverseHashTable","NVTraverse",montagedata$ds))
d1<-subset(montagedata,ds=="DRAM (T)")
d2<-subset(montagedata,ds=="NVM (T)")
d3<-subset(montagedata,ds=="Montage (T)")
d4<-subset(montagedata,ds=="Montage")
d5<-subset(montagedata,ds=="Dalí")
d6<-subset(montagedata,ds=="SOFT")
d7<-subset(montagedata,ds=="MOD")
d8<-subset(montagedata,ds=="Mnemosyne")
d9<-subset(montagedata,ds=="Pronto-Sync")
d10<-subset(montagedata,ds=="Pronto-Full")
d11<-subset(montagedata,ds=="NVTraverse")
lkdata = rbind(d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11)

ddply(.data=lkdata,.(ds,size),mutate,ops= mean(ops))->lkdata
lindata = rbind(lkdata[,c("ds","size","ops")])
lindata$ds <- factor(lindata$ds, levels=c("DRAM (T)", "NVM (T)", "Montage (T)", "Montage", "SOFT", "NVTraverse", "Dalí", "MOD", "Pronto-Full", "Pronto-Sync", "Mnemosyne"))

# Set up colors and shapes (invariant for all plots)
color_key = c("#12E1EA","#1245EA",
              "#FF69B4","#C11B14",
              "#660099","#6F2534","#1BC40F","#5947ff",
              "#FF8C00", "#F86945",
              "#191970")
names(color_key) <- levels(lindata$ds)

shape_key = c(2,1,0,18,20,25,17,15,16,62,4)
names(shape_key) <- levels(lindata$ds)

line_key = c(2,2,2,1,1,1,1,1,1,4,1)
names(line_key) <- levels(lindata$ds)

# Benchmark-specific plot formatting
legend_pos=c(0.237,0.2)
y_name="Throughput (ops/s)"
y_range_down = 15000

# Generate the plots
linchart<-ggplot(data=lindata,
                  aes(x=size,y=ops,color=ds, shape=ds, linetype=ds))+
  geom_line()+xlab("Size (B)")+ylab(y_name)+geom_point(size=4)+
  scale_shape_manual(values=shape_key[names(shape_key) %in% lindata$ds])+
  scale_linetype_manual(values=line_key[names(line_key) %in% lindata$ds])+
  theme_bw()+ guides(shape=guide_legend(title=NULL,ncol=2))+ 
  guides(color=guide_legend(title=NULL,ncol=2))+
  guides(linetype=guide_legend(title=NULL,ncol=2))+
  scale_color_manual(values=color_key[names(color_key) %in% lindata$ds])+
  scale_x_continuous(trans='log2',breaks=c(16,64,256,1024,4096),labels=c("16","64","256","1K","4K"))+
  scale_y_continuous(trans='log2',label=scientific_10,breaks=c(10000,100000,1000000,1000000,10000000),
                minor_breaks=c(2000,3000,4000,5000,6000,7000,8000,9000,20000,30000,40000,50000,60000,70000,80000,90000,200000,300000,400000,500000,600000,700000,800000,900000,2000000,3000000,4000000,5000000,6000000,7000000,8000000,9000000,20000000,30000000,40000000,50000000,60000000,70000000,80000000,90000000,200000000,300000000,400000000,500000000,600000000,700000000,800000000,900000000,2000000000))+
  coord_cartesian(xlim = c(16,4096), ylim = c(3000,2000000))+
  theme(plot.margin = unit(c(.2,0,-1.5,0), "cm"))+
  theme(legend.position=legend_pos,
    legend.background = element_blank(),
    legend.key = element_rect(colour = NA, fill = "transparent"))+
  theme(text = element_text(size = 18))+
  theme(axis.title.y = element_text(margin = margin(t = 0, r = 5, b = 0, l = 2)))+
  theme(axis.title.x = element_text(hjust =-0.105,vjust = 8.7,margin = margin(t = 15, r = 0, b = 10, l = 0)))

# Save all four plots to separate PDFs
ggsave(filename = paste("./hashtables_",t,".pdf",sep=""),linchart,width=8, height = 4, units = "in", dpi=300, title = paste("hashtables_",t,".pdf",sep=""))
}
