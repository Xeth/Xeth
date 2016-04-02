var RegistrarCollectionSimulator = Backbone.Collection.extend({

    fetch:function(){
        //this.reset(this.parse(XETH_bitprofile.listRegistrars({limit:100})));
    },

    parse:function(data){
        var result = [];
        for(var i in data){
            result.push({uri: data[i]});
        }
        return result;
    },

    observe:function(){
    
    }

});
