py#!/bin/bash
path=$1
filename=$2
newfilename=$3

echo "path = $path"
echo "filename = $filename"
echo "newfilename = $newfilename"

echo "We are finding '$filename' under the folder '$path'"

#find $path -name "*$filename*" | tac

count=1
for i in `find $path -name "*$filename*" | tac`
	do
		# \(\)表示分组 \1表示对前面匹配字符都后向引用
		newpath=`echo $i | sed "s@\(.*\)$filename@\1$newfilename@i"`
		echo $newpath
		sudo mv "$i" "$newpath"
		echo "${count}: Renaming $i to $newpath"
		let count++
	done
