var ContactSimulator = Contact.extend({

    save:function(){},

    destroy:function(){
        this.trigger("destroy", this);
    }

});

var AddressBookSimulator = AddressBook.extend({


    fetch:function(){
        this.reset();
    },

    create:function(data){
        var model = this.model(data);
        this.add(model);
        return true;
    },

    observe:function(){},

    model: function(data, options){
        return new ContactSimulator(data, {transactions:this.transactions});
    }

});
