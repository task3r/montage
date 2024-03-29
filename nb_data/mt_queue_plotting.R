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
tests<-c("thread")
for (t in tests){
read.csv(paste("./queues_",t,".csv",sep=""))->montagedata

montagedata$ds<-as.factor(gsub("FriedmanQueue","Friedman",montagedata$ds))
montagedata$ds<-as.factor(gsub("nbMontageMSQueue","nbMontage",montagedata$ds))
montagedata$ds<-as.factor(gsub("MontageMSQueue","Montage",montagedata$ds))
montagedata$ds<-as.factor(gsub("NVMMSQueue","NVM (T)",montagedata$ds))
montagedata$ds<-as.factor(gsub("MSQueue","DRAM (T)",montagedata$ds))
d1<-subset(montagedata,ds=="DRAM (T)")
d2<-subset(montagedata,ds=="NVM (T)")
d3<-subset(montagedata,ds=="nbMontage")
d4<-subset(montagedata,ds=="Montage")
d5<-subset(montagedata,ds=="Friedman")
lkdata = rbind(d1,d2,d3,d4,d5)

ddply(.data=lkdata,.(ds,thread),mutate,mops= mean(ops)/1000000)->lkdata_
lindata = rbind(lkdata_[,c("ds","thread","mops")])
lindata$ds <- factor(lindata$ds, levels=c("DRAM (T)","NVM (T)","nbMontage", "Montage","Friedman"))

# Set up colors and shapes (invariant for all plots)
color_key = c("#12E1EA","#1245EA",
              "#C11B14","#FF69B4","#809900")
names(color_key) <- levels(lindata$ds)

shape_key = c(2,1,18,4,20)
names(shape_key) <- levels(lindata$ds)

line_key = c(2,2,1,1,1)
names(line_key) <- levels(lindata$ds)

# Benchmark-specific plot formatting
legend_pos=c(0.7,0.8)
y_name="Throughput (Mops/s)"


# Generate the plots
linchart<-ggplot(data=lindata,
                  aes(x=thread,y=mops,color=ds, shape=ds, linetype=ds))+
  geom_line()+xlab("Threads")+ylab(y_name)+geom_point(size=4)+
  scale_shape_manual(values=shape_key[names(shape_key) %in% lindata$ds])+
  scale_linetype_manual(values=line_key[names(line_key) %in% lindata$ds])+
  theme_bw()+ guides(shape=guide_legend(title=NULL,ncol=1))+ 
  guides(color=guide_legend(title=NULL,ncol=1))+
  guides(linetype=guide_legend(title=NULL,ncol=1))+
  scale_color_manual(values=color_key[names(color_key) %in% lindata$ds])+
  scale_x_continuous(breaks=c(0,10,20,30,40,50,60,70,80,90,100),
      minor_breaks=c(-10))+
  coord_cartesian(xlim = c(-2, 40), ylim = c(0,11))+
  theme(plot.margin = unit(c(.2,0,-1.5,0), "cm"))+
  theme(legend.position=legend_pos,
  legend.background = element_blank(),
  legend.key = element_rect(colour = NA, fill = "transparent"))+
  theme(text = element_text(size = 12))+
  theme(axis.title.y = element_text(margin = margin(t = 0, r = 5, b = 0, l = 2)))+
  theme(axis.title.x = element_text(hjust =-0.13,vjust = 13.5,margin = margin(t = 22, r = 0, b = 10, l = 0)))

# Save all four plots to separate PDFs
ggsave(filename = paste("./queues_",t,".pdf",sep=""),linchart,width=4, height = 4, units = "in", dpi=300, title = paste("queues_",t,".pdf",sep=""))
}
