var ProfileValidator = Backbone.Collection.extend({

    isValidName:function(name){
        return (name==" ")?false:true;
    },
    isAvailable:function(data){
        return (data.id=="111")?false:true;;
    },
});
