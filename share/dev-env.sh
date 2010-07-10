# source this from your shell to mess with the current pito build

BUILD_DIR=src/pito/.obj

d=$PWD
while [ $d != / ] && [ ! -d $d/.git ] ; do
    d=`dirname $d`
done

export LD_LIBRARY_PATH="$d/$BUILD_DIR/plugin:$LD_LIBRARY_PATH"
export PATH="$d/$BUILD_DIR:$PATH"
