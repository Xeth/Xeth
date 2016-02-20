var Contact = Backbone.Model.extend({

    idAttribute: "alias",

    initialize:function(data, options){
        if(options.transactions){
            _(this).bindAll("resolve");
            var total = 0;
            var address = this.get("address");
            var bitprofile = this.get("bitprofile");
            var contact = this;
            options.transactions.each(function(transaction){
                if(contact._resolve(address, bitprofile, transaction)){
                    total++;
                }
            });
            this.set("transactions", total);
            this.listenTo(options.transactions, "add", this.resolve);
        }
    },

    save:function(){
        if(this.isNew()){

            return addressbook.addContact(this.toJSON());
        }else{

            return addressbook.editContact(this.toJSON());
        }
    },

    destroy:function(){
        return addressbook.removeContact(this.get("alias"));
    },

    resolve:function(transaction){
        var address = this.get("address");
        var bitprofile = this.get("bitprofile");
        if(this._resolve(this.get("address"), this.get("bitprofile"), transaction)){
            this.set("transactions", (this.get("transactions")||0)+1);
        }
    },

    _resolve:function(address, bitprofile, transaction){
        if(address==transaction.get("from")||address==transaction.get("to")||(bitprofile &&bitprofile==transaction.get("bitprofile"))){
            transaction.set("contact", this);
            return true;
        }
        return false;
    },

    sync:function(){}

});

var AddressBook = Backbone.Collection.extend({

    initialize:function(models, options){
        this.transactions = options?options.transactions:null;
    },

    fetch:function(){
        var contacts = addressbook.listContacts();
        if(contacts.length){
            this.reset(contacts);
        }else{
            if(this.length){
                this.reset();
            }
        }
    },

    resolve:function(transactions){
        this.transactions = transactions;
        for(var i in this.models){
            this.models[i].transactions = transactions;
            for(var j in transactions.models){
                this.models[i].resolve(transactions.models[j]);
            }
        }
    },

    rename:function(oldName, newName){

        if(addressbook.renameContact({oldName:oldName, newName:newName})){
            var contact = this.get(oldName);
            this.remove(contact, {silent:true});
            contact.set("alias", newName);
            this.add(contact, {silent: true});
            this.emit("update", contact);
            return true;
        }
        return false;
    },

    observe:function(){
        event.Contact.connect(this, Backbone.Collection.prototype.add);
    },

    model: function(data, options){
        return new Contact(data, {transactions:options.collection.transactions});
    }

});
