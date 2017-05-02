TUMRGBD_PATH=$1;
if [ ! -f $TUMRGBD_PATH/sequence.txt ]; then
   if [ ! -f ./associate.py ]; then
      wget -nv https://www.dropbox.com/s/fm4jwt34pi6r9w6/associate.py?dl=0 -O associate.py;
      chmod +x ./associate.py;
   fi
   ./associate.py $TUMRGBD_PATH/groundtruth.txt $TUMRGBD_PATH/rgb.txt >> ./temp.txt;
   ./associate.py ./temp.txt $TUMRGBD_PATH/depth.txt >> $TUMRGBD_PATH/sequence.txt;
   rm ./temp.txt;
fi